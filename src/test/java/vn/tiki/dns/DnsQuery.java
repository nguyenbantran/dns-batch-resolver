package vn.tiki.dns;

import dorkbox.network.DnsClient;
import io.netty.channel.embedded.EmbeddedChannel;
import io.netty.channel.socket.DatagramPacket;
import io.netty.handler.codec.dns.*;
import io.netty.util.internal.SocketUtils;
import org.junit.Assert;
import org.junit.Test;

import java.net.InetSocketAddress;
import java.util.ArrayList;
import java.util.List;


public class DnsQuery {
    public static void main(String[] args) throws Exception {

        var client = new DnsClient();
        var ans = client.resolve("google.com.", 5);
        System.out.println(ans);
    }

    @Test
    public void writeQueryTest() throws Exception {
        InetSocketAddress addr = SocketUtils.socketAddress("8.8.8.8", 53);
        EmbeddedChannel embedder = new EmbeddedChannel(new DatagramDnsQueryEncoder());
        List<DatagramDnsQuery> queries = new ArrayList<>(5);
        queries.add(new DatagramDnsQuery(null, addr, 1).setRecord(
                DnsSection.QUESTION,
                new DefaultDnsQuestion("1.0.0.127.in-addr.arpa", DnsRecordType.PTR)));
        queries.add(new DatagramDnsQuery(null, addr, 1).setRecord(
                DnsSection.QUESTION,
                new DefaultDnsQuestion("www.example.com", DnsRecordType.A)));
        queries.add(new DatagramDnsQuery(null, addr, 1).setRecord(
                DnsSection.QUESTION,
                new DefaultDnsQuestion("example.com", DnsRecordType.AAAA)));
        queries.add(new DatagramDnsQuery(null, addr, 1).setRecord(
                DnsSection.QUESTION,
                new DefaultDnsQuestion("example.com", DnsRecordType.MX)));
        queries.add(new DatagramDnsQuery(null, addr, 1).setRecord(
                DnsSection.QUESTION,
                new DefaultDnsQuestion("example.com", DnsRecordType.CNAME)));

        for (DatagramDnsQuery query: queries) {
            embedder.writeOutbound(query);

            DatagramPacket packet = embedder.readOutbound();
            Assert.assertTrue(packet.content().isReadable());
            packet.release();
            Assert.assertNull(embedder.readOutbound());
        }
    }
}
